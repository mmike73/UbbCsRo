package org.example.socialnetworkjavafx.Utils.Dtos;

import org.example.socialnetworkjavafx.Entities.Friendship;

import java.util.Optional;

public class FriendshipFilterDTO implements FilterDTO<Friendship> {
    private final Optional<String> username;
    private final Optional<String> initiator;
    private final Optional<Boolean> pending;

    public FriendshipFilterDTO(Optional<String> username, Optional<String> initiator, Optional<Boolean> pending) {
        this.username = username;
        this.initiator = initiator;
        this.pending = pending;
    }

    public Optional<String> getUsername() {
        return username;
    }

    public Optional<String> getInitiator() {
        return initiator;
    }

    public Optional<Boolean> getPending() {
        return pending;
    }

    public static class Builder {
        private String username;
        private String initiator;
        private Boolean pending;

        public Builder setUsername(String username) {
            this.username = username;
            return this;
        }

        public Builder setInitiator(String initiator) {
            this.initiator = initiator;
            return this;
        }

        public Builder setPending(Boolean pending) {
            this.pending = pending;
            return this;
        }

        public FriendshipFilterDTO build() {
            return new FriendshipFilterDTO(
                    Optional.ofNullable(username),
                    Optional.ofNullable(initiator),
                    Optional.ofNullable(pending)
            );
        }
    }
}
